%%%Last revision 2006/01/30, by Pascal.
%%%Changes include having Matlab do more of the heavy lifting than LabView and adding a ROI algorithm.
%%%THE ORIGINAL SCRIPT WAS ALTERED SOMEWHAT BY NATALI MARTINEZ ON SEP. 14, 2005
%%%ALTERATIONS INCLUDE:  CLEANING UP OF UNNECESSARY CODE/COMMENTS, ADDITION OF NUMERICAL INTEGRATION OF DATA,  

%This script is designed to input a data matrix (i.e., the data that would be contained in a datafile for post-processing) and corresponding background 
%matrix; program outputs 2D fit parameters. This script is designed to run in a MATLAB node in LabVIEW for on-the-fly data analysis.

%THIS PROGRAM IS A STRIPPED-DOWN VERSION OF THE IMAGEFITRING PROGRAM USED IN POST-PROCESSING

aa=1; %This is here as a flag to tell if Matlab script node is operating correctly.

%%%%%%%%%%%%%%%%%%%%%%%%%BEGINNING OF CODE%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
path('C:\instrumentvi\camera',path);
%This directory must contain gaussfitfunctionerrorslope.m and/or myfitfunctionR2.m.
%The path must also be correct for whichever computer this program is being run on.

%clear opticaldepthimagesingle;
clear opticaldepthcalcmatrix;
clear rawimageatom;
clear rawimageback;

%%%%%SPECIFICS OF FITTING ROUTINES, CAMERA AND AVERAGING SETTINGS%%%%%
sampleinterleave=S(1);    %(total column size in each data file should be an integer multiple of sampleinterleave) for big matrices form a matrix using only one point for every sampleinterleave points in a row/column
pixelsize=S(2);           %the real size for the object in meter unit for a pixel
CCDbinning=S(3);     %total binning; number of pixels binned when first recording data
prebinning=softwarebinsize*CCDbinning*sampleinterleave;
cutborders=S(4); %5 (REMEMBER THIS IS DONE AFTER SAMPLEINTERLEAVE); number of column and rows to trim on either side of the data matrix
numberforscale=S(5);     %number of column and rows to scale the base level of atom and background images
limit=S(6);     %number of column and rows at the corners to find the uncertainities/noise
guesssmoothsize=S(7);  %number of points to average for guessing

f=fullrawimageatom;
fullsizefull=size(fullrawimageatom);
fullrowfull=fullsizefull(1); %no. of rows; form matrix from only part of the data
fullcolumnfull=fullsizefull(2);

%%%SCALING OF BASE LEVEL%%%
if scalebaselevel==1
     sumylowxlow=sum(sum(fullrawimageatom(1:numberforscale,1:numberforscale)));;
     sumylowxhigh=sum(sum(fullrawimageatom(1:numberforscale,fullcolumnfull-numberforscale:fullcolumnfull)));
     sumyhighxlow=sum(sum(fullrawimageatom(fullrowfull-numberforscale:fullrowfull,1:numberforscale)));
     sumyhighxhigh=sum(sum(fullrawimageatom(fullrowfull-numberforscale:fullrowfull,fullcolumnfull-numberforscale:fullcolumnfull)));
     baselevelatom=sumylowxlow+sumylowxhigh+sumyhighxlow+sumyhighxhigh;
     sumylowxlow=sum(sum(fullrawimageback(1:numberforscale,1:numberforscale))); %there was an error I think so changed from average to sum since 
     sumylowxhigh=sum(sum(fullrawimageback(1:numberforscale,fullcolumnfull-numberforscale:fullcolumnfull)));
     sumyhighxlow=sum(sum(fullrawimageback(fullrowfull-numberforscale:fullrowfull,1:numberforscale)));
     sumyhighxhigh=sum(sum(fullrawimageback(fullrowfull-numberforscale:fullrowfull,fullcolumnfull-numberforscale:fullcolumnfull)));
     baselevelback=sumylowxlow+sumylowxhigh+sumyhighxlow+sumyhighxhigh;
     fullrawimageatom=fullrawimageatom*baselevelback/baselevelatom;
end

%%%INTERLEAVING OF DATA%%%;  uses every sampleinterleave points and throws away rest of data
i=0; j=0; v=0;
for i=1:fullrowfull/sampleinterleave
    for j=1:fullcolumnfull/sampleinterleave
        for v=1:sampleinterleave
            temp1(v)=sum(fullrawimageatom(((i-1)*sampleinterleave+1):i*sampleinterleave,((j-1)*sampleinterleave+v))); %this does the software interleaving/sampling
            temp2(v)=sum(fullrawimageback(((i-1)*sampleinterleave+1):i*sampleinterleave,((j-1)*sampleinterleave+v))); %interleaving for background
        end
        rawimageatom(i,j)=sum(temp1); %stores the software interleaved/sampled data
        rawimageback(i,j)=sum(temp2); %stores the software interleaved/sampled data
    end
end
sizefull=size(rawimageatom);
rowfull=sizefull(1);       %number of rows after interleaving
columnfull=sizefull(2); %number of columns after interleaving
xoffsetfull=fullxoffset/sampleinterleave; %adjust peak position to new size
yoffsetfull=fullyoffset/sampleinterleave; %adjust peak position to new size

%%%CUT DATA OFF FROM EDGES%%%; remember this is done after interleaving
i=0; j=0;
for i=1+cutborders:rowfull-cutborders,
    for j=1+cutborders:columnfull-cutborders,
        cutimageatom(i-cutborders,j-cutborders)=rawimageatom(i,j);
        cutimageback(i-cutborders,j-cutborders)=rawimageback(i,j);
    end
end
sizes=size(cutimageatom);
row=sizes(1); %number of rows after cutting data off of edges
column=sizes(2); %number of columns after cutting data off of edges
xoffset=xoffsetfull-cutborders; %Determines guess for peak position
yoffset=yoffsetfull-cutborders; %Determines guess for peak position

%%%ABS VALUE AND OPTICAL DEPTH%%%
cutimageatom=abs(cutimageatom);   %abs gives the absolute value and complex magnitude
cutimageback=abs(cutimageback);
opticaldepthimagesingle=(log(cutimageatom)-log(cutimageback))*(-1); %makes absorption positive

%%%DATA FITTING - 2D FITS%%%
%GENERATE GUESSES AND BOUNDS%
Zguess=filter2(ones(guesssmoothsize,guesssmoothsize),opticaldepthimagesingle(:,:))/guesssmoothsize^2; %atom-back/OD, smoothed for finding guesses   
amplitude=max(max(Zguess));     %this will give trouble if slope is too big
sigx=column/10;
sigy=row/10;
%xoffset=row/2; %xoffset is now input from LabView; determined by binning by 8 and choosing max bin rather than max pixel.
%yoffset=column/2; %same comment for yoffset as for xoffset.
averageylowxlow=sum(sum(Zguess(1:5,1:5)))/25;;
averageylowxhigh=sum(sum(Zguess(1:5,column-5:column)))/25;
averageyhighxlow=sum(sum(Zguess(row-5:row,1:5)))/25;
averageyhighxhigh=sum(sum(Zguess(row-5:row,column-5:column)))/25;
offset=(averageylowxlow+averageylowxhigh+averageyhighxlow+averageyhighxhigh)/4 ;
slopex=((averageylowxhigh+averageyhighxhigh)-(averageylowxlow+averageyhighxlow))/(2*column);
slopey=((averageyhighxlow+averageyhighxhigh)-(averageylowxlow+averageylowxhigh))/(2*row);
     
InitialConditions=[amplitude, sigx, sigy, xoffset, yoffset,offset,slopex,slopey];
%lowerbound=[0, 1, 1, 10, 10, -3, 0, 0,-.01,-.01];
%upperbound=[1, 50, 50, 90, 90, 3, 1, 1,.01,.01];
temp5=size(InitialConditions);
numberofparameters=temp5(2); %number of 2D fit parameters
 
%%%STATISTICS OF IMAGE%%%
%Weird things happen when you calculate these with smoothed images!!!
%get estimate of noise, you need to subtract image from background because of fringes and variations in intensity
average1=sum(sum(cutimageatom(1:limit,1:limit)-cutimageback(1:limit,1:limit)))/limit^2;
rms1=sqrt(sum(sum((cutimageatom(1:limit,1:limit)-cutimageback(1:limit,1:limit)).^2))/limit^2);
rmsdeviation1=sqrt(rms1^2-average1^2);
   
average2=sum(sum(cutimageatom(row-limit:row,1:limit)-cutimageback(row-limit:row,1:limit)))/limit^2;
rms2=sqrt(sum(sum((cutimageatom(row-limit:row,1:limit)-cutimageback(row-limit:row,1:limit)).^2))/limit^2);
rmsdeviation2=sqrt(rms2^2-average2^2);
   
average3=sum(sum(cutimageatom(1:limit,column-limit:column)-cutimageback(1:limit,column-limit:column)))/limit^2;
rms3=sqrt(sum(sum((cutimageatom(1:limit,column-limit:column)-cutimageback(1:limit,column-limit:column)).^2))/limit^2);
rmsdeviation3=sqrt(rms3^2-average3^2);

average4=sum(sum(cutimageatom(row-limit:row,column-limit:column)-cutimageback(row-limit:row,column-limit:column)))/limit^2;
rms4=sqrt(sum(sum((cutimageatom(row-limit:row,column-limit:column)-cutimageback(row-limit:row,column-limit:column)).^2))/limit^2);
rmsdeviation4=sqrt(rms4^2-average4^2);
   
error=abs((rmsdeviation1+rmsdeviation2+rmsdeviation3+rmsdeviation4)/(4))

%%%CREATE FITTING MATRICES%%%
%SEE EXPLANATION ON PG. 78 OF PRIYA'S NOTEBOOK 2 %
errorod(1:row*column)=error/(sum(sum(cutimageback))/(row*column));     %normalized error - relative to average pixel value
xvec=1:column;
yvec=1:row;
[ydata,xdata]=meshgrid(yvec,xvec);     %rows of output array xdata are copies of vector xvec; columns of output array ydata are copies of vector yvec
ydata=transpose(ydata); xdata=transpose(xdata);
numberofpoints=column*row*ones(column,row);     %matrix in which each entry is the number of points 
coordmatrix=[ydata(:),xdata(:),errorod(:),numberofpoints(:)];
 
%%%ACTUAL FITTING PROCEDURES%%%  
Z2=(opticaldepthimagesingle(:)./(errorod(:)*sqrt(column*row)));     %flattened(1D) list of image weighted by uncertainties, not smoothed
options=statset('MaxIter',12);

%%%nlinfit method%%%
[P,r,J,iteractual]=nlinfit(coordmatrix,Z2(:),@gaussfitfunctionerrorsslope,InitialConditions,options);     % expecting data divided by weight and sqrt(number of points)

%%%Gauss-Newton least squares%%%
%maxiter = 10;
%tol = 10e-5;
%P = InitialConditions';
    %for iter = 1:maxiter
        %[r,J] = feval(@myfitfunctionR2,P,coordmatrix,Z2);
        %g = J'*r;
        %nrmg = norm(g);
        %fprintf('iter: %2i  norm(g) = %7.3e\n',iter,nrmg);
        %if nrmg < tol break; end

        %f = 0.5*r'*r;
        %B = J'*J+min(10e-4,2*f)*speye(size(J,2));
        %P = P - B\g;
    %end
%P=P';

%%%REMOVE THE GRADIENT FROM THE DATA%%% ; that is, remove background and slope from data
gradmatrix=(ydata(:)-P(5))*P(8)+(xdata(:)-P(4))*P(7)+P(6);
nogradoddata=opticaldepthimagesingle(:)-gradmatrix(:);
nogradodmatrix = reshape(nogradoddata, size(ydata));  %returns an n-dimensional array with same elements as nograddata but reshaped to size(ydata)

%%%Generate plot of optical density based on fitted parameters, remove distortion of data due to dividing by weight and sqrt(number of points)%%%
dummyerrorod(1:row*column)=1; 
dummynumberofpoints=ones(row,column); 
coordmatrix=[ydata(:),xdata(:),dummyerrorod(:),dummynumberofpoints(:)];
opticaldepthcalcvector=gaussfitfunctionerrorsslope(P, coordmatrix);     %optical depth calculated from fit paramters
opticaldepthcalcmatrix=reshape(opticaldepthcalcvector,size(ydata));

ci=nlparci(P,r,J);%error in the fit parameters 95% confidence interval
sdev=(ci(:,2)-ci(:,1))/4;%turn confidence interval into 1 sigma             
weightedresidue3D=(Z2(:)-gaussfitfunctionerrorsslope(P, coordmatrix)); %weighted residues
chi3D=(transpose(weightedresidue3D)*weightedresidue3D)
%%%CALCULATE CHI-SQUARED%%%
chisquared=sum(sum((opticaldepthimagesingle-opticaldepthcalcmatrix).*(opticaldepthimagesingle-opticaldepthcalcmatrix)))/((row*column-1)*errorod(1)^2);
%Fraction absorption is p(1)

%%%CALCULATING OD INTEGRAL%%%
totalod=0;
odintegral=0;
%%%Sum of the optical depth to get the total OD%%%
i=0; j=0; pixelcount=0;
for i=1:row
     for j=1:column
          tempindex=(i-1).*column+j; %converts the 2-D index to 1-D so reads from beginning of first row then from beginning of second row and so on
          totalod=totalod+nogradoddata(tempindex);
          pixelcount=pixelcount+1;
     end
end

odintegral=totalod*(prebinning*pixelsize)^2; %convert to real units, take care of binning effects, etc
odintegralerror=errorod(1)*sqrt(row*column)*(prebinning*pixelsize)^2;

%%%OUTPUT PARAMETERS%%%
%These are actually output as P, but names left in so they can be checked in Matlab more easily.
peakod=P(1);
P(2)=pixelsize*prebinning*abs(P(2));     %sigmax in meters
P(3)=pixelsize*prebinning*abs(P(3));     %sigmay in meters
xcenter=P(4); %xoffset
ycenter=P(5); %yoffset
offsetfit=P(6);

%%%THE END%%%