import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

df=pd.read_csv("UScrime.dat")

crime_data = ols("y ~ poverty", data=df)




 
 