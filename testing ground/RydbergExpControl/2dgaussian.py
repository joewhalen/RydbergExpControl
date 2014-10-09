#http://wiki.scipy.org/Cookbook/FittingData#head-11870c917b101bb0d4b34900a0da1b7deb613bf7

from numpy import *
from scipy import optimize
from pylab import *

def gaussian(height, center_x, center_y, width_x, width_y,offset):
    """Returns a gaussian function with the given parameters"""
    width_x = float(width_x)
    width_y = float(width_y)
    return lambda x,y: height*exp(-(center_x-x)**2/(2*width_x**2)
                                  -(center_y-y)**2/(2*width_y**2))+offset
    #return lambda x,y: height*exp(
    #            -((center_x-x)/width_x)**2/2+((center_y-y)/width_y)**2/2)

def moments(data):
    """Returns (height, x, y, width_x, width_y)
    the gaussian parameters of a 2D distribution by calculating its
    moments """
    total = data.sum()
    X, Y = indices(data.shape)
    x = (X*data).sum()/total
    y = (Y*data).sum()/total
    col = data[:, int(y)]
    width_x = sqrt(abs((arange(col.size)-y)**2*col).sum()/col.sum())
    row = data[int(x), :]
    width_y = sqrt(abs((arange(row.size)-x)**2*row).sum()/row.sum())
    height = data.max()
    offset = data.min()
    if isnan(width_x):
        width_x = data.shape[0]
    if isnan(width_y):
        width_y = data.shape[1]
    print height, x, y, width_x, width_y, offset
    return height, x, y, width_x, width_y, offset

def fitgaussian(data):
    """Returns (height, x, y, width_x, width_y)
    the gaussian parameters of a 2D distribution found by a fit"""
    params = moments(data)
    errorfunction = lambda p: ravel(gaussian(*p)(*indices(data.shape)) -
                                 data)
    p, success = optimize.leastsq(errorfunction, params)
    return p

if __name__ == "__main__":
    # Create the gaussian data
    #data = gaussian(3, 100, 100, 20, 40)(Xin, Yin)# + random.random(Xin.shape)
    data = np.genfromtxt('temp.csv',delimiter='\t')
    (xLim,yLim) = np.shape(data)
    Xin, Yin = mgrid[0:(xLim-1),0:(yLim-1)]

    params = fitgaussian(data)

    """#uncomment to show graph
    fit = gaussian(*params)
    matshow(data, cmap=cm.gist_earth_r)
    contour(fit(*indices(data.shape)), cmap=cm.copper)
    ax = gca()
    (height, x, y, width_x, width_y,offset) = params
    
    text(0.95, 0.05, "
    x : %.1f
    y : %.1f
    width_x : %.1f
    width_y : %.1f" %(x, y, width_x, width_y),
            fontsize=16, horizontalalignment='right',
            verticalalignment='bottom', transform=ax.transAxes)
    
    show()"""

    ##print height
    ##print width_x,width_y
    f = open('fitparams.txt','w')
    for i in params:
        f.write('%3.3e\n'%i)
    f.close()
    #return 0
