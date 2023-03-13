# -*- coding: utf-8 -*-
"""
Created on Fri Mar 10 10:53:56 2023

@author: DISRCT
"""

import matplotlib.pyplot as plt
import pyodbc
import numpy as np


server = 'CT-C-00188\SQLEXPRESS'
database = 'tempdb'
driver= '{SQL Server}'
cnxn = pyodbc.connect('DRIVER={SQL Server};SERVER='+server+';DATABASE='+database+';Trusted_Connection=yes')
cursor = cnxn.cursor()
cursor.execute("SELECT temp, timestamp, umid FROM dbo.Sensor")

row = cursor.fetchone()
Umidade = []
tempo = []
Temperatura = []

while row:
    Temperatura.append(row[0])
    Umidade.append(str(row[2]))
    tempo.append(":".join(str(row[1]).split(' ')[1].split(':')[0:2]))
    row = cursor.fetchone()
    

listX = [tempo[i] for i in range(0, len(tempo), 10)]
listY = [Temperatura[i] for i in range(0, len(Temperatura), 10)]

plt.plot(listX, listY, label="temperatura")

plt.xticks(rotation = 60)



cursor = cnxn.cursor()
cursor.execute("SELECT temp, timestamp, umid FROM dbo.Sensor")
result = len(cursor.fetchall())
print("Quantidade de inserções no banco:", result)