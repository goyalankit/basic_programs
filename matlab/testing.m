close all;
clear;
clc;
first{1,2}=csvread('1_1_WithoutHeaders.csv',1,0);
first{1,1}=csvread('1_1_WithHeaders.csv',1,0);
Fs=5000;
Power1{1,1}(:,1)=first{1,1}(:,3);
Power1{1,2}(:,1)=first{1,2}(:,2);
% figure, plot(first{1,1}(:,1),Power1{1,1}(:,1));
% figure, plot(first{1,2}(:,1),Power1{1,2}(:,1),'r');
Energy{1,1}(1,1)=0;
Energy{1,2}(1,1)=0;
for i=1:2
    baseline(1,i)=mean(Power1{1,i}(1:1000,1));
    Power{1,i}=Power1{1,i}-baseline(1,i);

    NFFT(1,i)=size(Power{1,i},1);

    % Compute power spectrum of fake signal:
       [Pxx2{1,i},F2{1,i}] = psd(Power{1,i}(:,1), NFFT(1,i), Fs);
       Pxx{1,i}=Pxx2{1,i}(3:size(Pxx2{1,i},1),1);
       F{1,i}=F2{1,i}(3:size(F2{1,i},1),1);
    for j=2:size(Power{1,i},1)
        Energy{1,i}(j,1)=Energy{1,i}(j-1,1)+Power{1,i}(j-1,1);
   end
   Energy{1,i}=Energy{1,i}/Fs; %Answer in mJ (milliJoules)
   Tenergy(1,i)=Energy{1,i}(size(Energy{1,i},1),1);
   Tenergy(1,i)
end
figure, plot(first{1,1}(:,1),Power{1,1}(:,1));
figure, plot(first{1,2}(:,1),Power{1,2}(:,1),'r');
%i figure, plot(first{1,1}(:,1),Energy{1,1}(:,1));
% figure, plot(first{1,2}(:,1),Energy{1,2}(:,1),'r');
h1 =  figure, plot(F{1,1}(:,1),Pxx{1,1}(:,1));
h2 =  figure, plot(F{1,2}(:,1),Pxx{1,2}(:,1),'r');
%saveas(h1, 'psd_1_1_with', 'jpg')
%saveas(h1, 'psd_2_2_with', 'jpg')
