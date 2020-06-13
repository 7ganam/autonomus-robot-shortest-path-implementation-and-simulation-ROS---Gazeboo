m=250;
n=250;

A = imread('image_250_0.jpg');
b=A(:,:,3)
for k=1:3
for i=1:m
    for j=1:n
        if A(i,j,k)<180
            A(i,j,k)=0;
        else
            A(i,j,k)=255;
        end
    end
end
end
fid=fopen('rnodes.TXT','r');
tline = fgetl(fid);
counter=0
c=[];
while ischar(tline)
  
    counter=counter+1;
    x = str2num(tline);
    c(counter)=x;
    tline = fgetl(fid);
end

fclose(fid);
m=size(c,2);
i=0;
% A=A(2:60,2:60);
for i=1:2:m % we added one beause matlab index start from one this shouldn't be added in c++
A( c(i)+1 , c(i+1)+1 ,1 )=100;
A( c(i)+1 , c(i+1)+1 ,2 )=150;
A( c(i)+1 , c(i+1)+1 ,3 )=50;
end
 imtool(A);