function output = stretch(input, t1, t2)
input(input<=t1)=0;
input(input>=t2)=255;
input(t1<input<t2)=(255/(t2-t1))*(input-t1);    
output=uint8(input);


end