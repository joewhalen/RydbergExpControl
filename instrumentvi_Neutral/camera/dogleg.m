function p = dogleg(H,g,d);

pb = -H\g;
if norm(pb) <= d
    p = pb;
else
    pu = -(g'*g)/(g'*H*g)*g;
    if norm(pu) >= d
        p = d*pu/norm(pu);
    else
        %compute tau
        pbu2 = (pb-pu)'*(pb-pu);
        pubu = pu'*(pb-pu);
        pu2 = pu'*pu;
        a = pbu2;
        b = 2*(pubu-pbu2);
        c = pu2-2*pubu+pbu2-d^2;
        tau = (-b+sqrt(b^2-4*a*c))/(2*a);
        p = pu + (tau-1)*(pb-pu);
    end
end
