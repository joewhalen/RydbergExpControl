function [x,iter] = MyLM(func,x,tol,maxiter,prt,varargin)
%
% Levenberg-Marquardt
% Solve nonlinear least squares
%
% Usage: [x,iter] = MyLM(func,x,tol,maxiter,prt,p1,p2,...)
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

dmax = 5;
d = 2;
eta = 0.1;

for iter = 1:maxiter
    [r,J] = feval(func,x,varargin{:});
    g = J'*r;
    nrmg = norm(g);
    if prt
        fprintf('iter: %2i  norm(g) = %7.3e\n',iter,nrmg);
    end
    if nrmg < tol break; end

    f = 0.5*r'*r;
    B = J'*J+min(10e-4,2*f)*speye(size(J,2));
    
    %get p
    p = dogleg(B,g,d);
    
    %trust region procedure
    rn = feval(func,x+p,varargin{:});
    fn = 0.5*rn'*rn;
    rho = (f-fn)/(-p'*g-0.5*p'*B*p);
    if rho < 1/4
        d = (1/4)*d;
    elseif rho > 3/4 & norm(p) == d
        d = min(2*d,dmax);
    end
    if rho > eta
        x = x+p;
    end
end
