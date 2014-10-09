batchfile = char('\\Barium\data\RedMOT\09.07.04\redMOTlife2035.batch')
%batchfile = char('\\Barium\data\RedMOT\09.07.04\redMOTlife2230.batch')
%batchfile = char('\\Barium\data\RedMOT\09.07.04\redMOTlife2236.batch')
%batchfile = char('\\Barium\data\RedMOT\09.07.04\redMOTliferempump2329.batch')

[file imagevco vcovoltage motdetuning d delay]=textread(batchfile, '%q %f %f %f %f %f','commentstyle','matlab')%read in all files, no limit
temp=size(imagevco);
basenamesize=temp(1);%automatically determine how may files in batch associated with this basename
q=[basenamesize]% array of number of data files in each batch

for k=1:1
    %fullpath = char(strcat('\\Barium\data\RedMOT\09.07.04\',file(k),'atoms','.dat'));
    %fullpath2 = char(strcat('\\Barium\data\RedMOT\09.07.04\',file(k),'back','.dat'));
    fullpath = char('\\Barium\data\RedMOT\ElectrimImages\172137dan 09-16-2004.txt');
    s=dlmread(fullpath);
    s=transpose(s);
    t=0;%dlmread(fullpath2);
    u=s;
    figure(1)
    %h=pcolor(u);
    %subplot(6, 3, k); 
    subplot(2,1,1); h = surf(u,'LineStyle','none');
    view([0 90])
    rotate(h,[0 0 1],-90)
    hold off
    subplot(2,1,2); h = surf(u,'LineStyle','none');
    view([90 0])
    hold on
    title(char('172137dan 09-16-2004.txt'));
end
