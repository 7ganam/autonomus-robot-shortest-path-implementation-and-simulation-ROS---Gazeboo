/home/ganam/Desktop/final 1/250 maps
m=250;
n=250;

A = imread('map 0.jpg');
A= imresize(A,[m , n]);
imtool(A)
imwrite(A,'image_250_0.jpg')
% 
% 
% for k=1:3
%   for i=1:m
%     for j=1:n
%         if A(i,j,k)<180
%            A(i,j,1)=0;
%            A(i,j,2)=0;
%            A(i,j,3)=0;
%         else
%             A(i,j,k)=255;
%         end
%     end
%   end
% end
AA=A;
% imtool(A)
% k=1;
% % for k=1:3
% %   for i=1:m
% %     for j=1:n
% %         if A(i,j,k)==0
% %              for ii =1:m
% %                 for jj=1:m
% %                     if sqrt((ii-i)^2+(jj-j)^2)<1.5 
% %                      AA(ii,jj,k)=0;
% %                     end
% %                 
% %                 end
% %              end
% %         end
% %     end
% %   end
% % end


