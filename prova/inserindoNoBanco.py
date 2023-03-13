
import requests
import json
import pyodbc
import time

url = 'https://avaliacao-iot-default-rtdb.firebaseio.com/'
proxies = {'https':"https://disrct:etsds10243110@10.224.200.26:8080"}

url_temperatura = url + 'JoaoPedro/Sensor/temperatura.json'
url_umidade = url + 'JoaoPedro/Sensor/umidade.json'


def sinal():
    
    temperatura = float(requests.get(url_temperatura, proxies=proxies).content)
    umidade = float(requests.get(url_umidade, proxies=proxies).content)
    
    return (temperatura, umidade)

def InserirBD(sinal):
    server = 'CT-C-00188\SQLEXPRESS'
    database = 'tempdb'
    cnxn = pyodbc.connect('DRIVER={SQL Server};SERVER='+server+';DATABASE='+database+';Trusted_Connection=yes')
    cursor = cnxn.cursor()
    cursor.execute(f"INSERT dbo.Sensor (temp, umid) VALUES ({sinal[0]},{sinal[1]});")
    cnxn.commit()
    print("Inserido com sucesso!")


def apresentar(sinal):
    print(f"Temperatura: {sinal[0]}")
    print(f"Umidade: {sinal[1]}")
    
    
while True:
    valores = sinal()
    apresentar(valores)
    InserirBD(valores)
    time.sleep(10)