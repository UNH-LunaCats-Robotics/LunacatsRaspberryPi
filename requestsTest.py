import requests

while True:
    r = requests.get("http://10.0.10.11:3000/cmd",auth=('tester','test'))
    print r.status_code
