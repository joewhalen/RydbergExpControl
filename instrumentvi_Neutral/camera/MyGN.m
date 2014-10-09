function [x,iter] = MyGN(func,x,tol,maxiter,prt,varargin)
%
% Gauss-Newton
% Solve nonlinear least squares
%
% Usage: [x,iter] = MyGN(func,x,tol,maxiter,prt,p1,p2,...)
%
%       input:  func = function returning [r, J]
%                  x = initial guess
%                tol = tolerance
%            maxiter = maximum iteration number
%                prt = boolean (whether to print each step)
%          p1,p2,... = paramaters required by f(optional)
%
%         output:  x = approximate solution (root of f)
%               iter = iteration number used (optional)
%
alpha0 = 1;
c=10e-4;
rho=0.5;
for iter = 1:maxiter
   [r,J] = feval(func,x,varargin{:});
   g = J'*r;
   nrmg = norm(g);
   if prt
       fprintf('iter: %2i  norm(g) = %7.3e\n',iter,nrmg);
   end
   if nrmg < tol break; end

   f = 0.5*r'*r;
   B = J'*J;%+min(10e-4,2*f)*speye(size(J,2));
   p = -(B\g);

   f0=f;
   alpha=alpha0;
   r = feval(func,x+alpha*p,varargin{:});
   f=0.5*r'*r;
   while f > f0+c*alpha*g'*p
       r = feval(func,x+alpha*p,varargin{:});
       f=0.5*r'*r;
       alpha=rho*alpha;
   end
   x = x + alpha*p;
end