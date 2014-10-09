close all
clear all

matrixsize=[1280 1024]; %This could be read in from .batch file values if necessary.

%Read in binary file created in LabView
fid=fopen('2dfits\20050818atomstestfitB.bny','rb','ieee-be');
%LabView saves binary in "big endian" ('be') format: most significant bit in
%lowest memory address. Matlab needs this info to import binary file correctly.
atomsmatrix=fread(fid,matrixsize,'*int16');
fclose(fid);
atomsize=size(atomsmatrix);
%LabView and Matlab treat matrix coordinates differently.
%(0,0) for LabView is lower left corner; for Matlab is upper left corner.
%Therefore, flip about horizontal axis.
atomsmatrix=flipud(atomsmatrix); 

%Load background file
fid=fopen('2dfits\20050818backtestfitB.bny','rb','ieee-be');
bgmatrix=fread(fid,matrixsize,'*int16');
fclose(fid);
bgsize=size(bgmatrix);
bgmatrix=flipud(bgmatrix);

%Image = Atoms - Background
imagematrix=atomsmatrix-bgmatrix;

%Plot results; 'imagesc' command creates an intensity plot with a minimum
%of fuss.  Just choose the coolest looking color map.
figure(100) %Just atoms and just background
subplot(2,2,1)
imagesc(atomsmatrix);
subplot(2,2,2)
imagesc(bgmatrix);
colormap(summer);
figure(101) %The actual image
imagesc(imagematrix,[0 1]);
colormap(summer);