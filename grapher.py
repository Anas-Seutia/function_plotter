import sys
import matplotlib.pyplot as plt
import csv

def plot3d():

    X = []
    Y = []
    Z = []
    
    with open("coefficients.txt", 'r') as datafile:
        plotting = csv.reader(datafile, delimiter=',')
    
        for ROWS in plotting:
            X.append(float(ROWS[0]))
            Y.append(float(ROWS[1]))
            Z.append(float(ROWS[3]))

    fig = plt.figure()
    ax = plt.axes(projection='3d')
    ax.scatter(X, Y, Z, c=Z)
    ax.set_title('3D plot of function')
    plt.show()
    
def main():
    plot3d()

if __name__ == "__main__":
    main()




