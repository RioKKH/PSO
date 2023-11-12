#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import numpy as np
import matplotlib.pyplot as plt
import pandas as pd

from mpl_toolkits.mplot3d import Axes3D
from sklearn.linear_model import LinearRegression


def load(fin:str) -> pd.DataFrame:
    """Load data from csv file."""
    names = ['x1', 'x2', 'y']
    df = pd.read_csv(fin, names=names)
    return df

def fit(df:pd.DataFrame) -> LinearRegression:
    """Fit a linear regression model."""
    X = df[['x1', 'x2']]
    y = df['y']
    model = LinearRegression()
    model.fit(X, y)
    #df['z_pred'] = model.predict(X)
    return model

def plot(df:pd.DataFrame, model:LinearRegression) -> None:
    # Retrieving the coefficients and intercept from the fitted model
    coefficients = model.coef_
    intercept = model.intercept_
    print('Coefficients: ', coefficients)
    print('Intercept: ', intercept)

    # Creating a grid of values
    x1_grid, x2_grid =\
        np.meshgrid(np.linspace(df['x1'].min(), df['x1'].max(), 100),
                    np.linspace(df['x2'].min(), df['x2'].max(), 100))
    flat_grid = np.c_[x1_grid.ravel(), x2_grid.ravel()]
    #flat_grid = np.array([x1_grid.flatten(), x2_grid.flatten()]).T

    y_pred = model.predict(flat_grid).reshape(x1_grid.shape)

    # Plotting the fitted plane
    fig = plt.figure(figsize=(8, 6))
    ax = fig.add_subplot(111, projection='3d')

    # Scatter plot
    sc = ax.scatter(df['x1'], df['x2'], df['y'], c=df['y'], cmap='viridis')

    # Plotting the fitted plane
    ax.plot_surface(x1_grid, x2_grid, y_pred,
                    alpha=0.2, rstride=100, cstride=100)

    # Labels
    ax.set_xlabel('X1')
    ax.set_ylabel('X2')
    ax.set_zlabel('Y')

    # Adding a color bar
    cbar = plt.colorbar(sc)
    cbar.set_label('Y values')

    # Show plot
    plt.show()

