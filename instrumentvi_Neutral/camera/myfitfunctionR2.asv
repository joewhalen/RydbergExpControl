function [r,J] = myfitfunction(coeffs, data, Z2);

amplitude = coeffs(1);
sigx = coeffs(2);
sigy = coeffs(3);
xoffset=coeffs(4);
yoffset=coeffs(5);
offset = coeffs(6); % Extract the coefficients from the vector
slopex=coeffs(7);
slopey=coeffs(8);

x = data(:, 1); % Split the data matrix into x and y vectors
y = data(:, 2);
w = data(:, 3);%matrix of errors
numberofpoints=data(:,4);%matrix in which each entry is the number of points
sqrtnumbpoints=sqrt(numberofpoints(1,1)); %sqqrt of number of points
%offset=1000;
%amplitude=-5000;
%xoffset=42;
%yoffset=46;
%slopex=-.0001;
%slopey=.0003;

wsqnp = 1./(w*sqrtnumbpoints);
temp = exp(-(((x- xoffset).^2)/(2*sigx^2))-(((y- yoffset).^2)/(2*sigy^2)));
r = ((offset+slopex*(x-xoffset)+slopey*(y-yoffset)) +  ...
   amplitude*temp).*wsqnp-Z2;
if nargout == 2
   J = [temp.*wsqnp, amplitude*temp.*(x-xoffset).^2/sigx^3.*wsqnp,  ...
    amplitude*temp.*(y-yoffset).^2/sigy^3.*wsqnp, ...
    (-slopex+amplitude*temp.*(2*x-2*xoffset)*1/(2*sigx^2)).*wsqnp, ...
    (-slopey+amplitude*temp.*(2*y-2*yoffset)*1/(2*sigy^2)).*wsqnp, ...
    wsqnp, (x-xoffset).*wsqnp, (y-yoffset).*wsqnp];
end
