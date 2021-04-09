import requests

def getMovie(movie, myKey):
    parameters = {"APPID": myKey, 'q':movie}
    url = 'http://www.omdbapi.com/?i=tt3896198&apikey=841ba8d4'
    res = requests.get(url, parameters)
    return eval(res.content.decode('utf-8'))

myKey = {http://www.omdbapi.com/?i=tt3896198&apikey=841ba8d4}
print(myKey)
myKey = eval(myKey)['movies']
movie = 'lion king'
res = getMovie(movie, myKey)
print('Movie:',res['name'])


import requests

def getMovie(myKey, movie):
    parameters = {'s':movie, 'type':'movie', 'y':2019}
    res = requests.get(myKey, parameters)
    return eval(res.content.decode('utf-8'))

myKey = 'http://www.omdbapi.com/?i=tt3896198&apikey=841ba8d4'
print(myKey)
movie = 'lion king'
res = getMovie(myKey, movie)
print('Movie:',res['Search'])


import requests

def getMovie(myKey, movie):
    parameters = {'s':movie, 'type':'movie', 'y':2019}
    res = requests.get(myKey, parameters)
    return eval(res.content.decode('utf-8'))

myKey = 'http://www.omdbapi.com/?i=tt3896198&apikey=841ba8d4'
print(myKey)
movie = 'lion king'
res = getMovie(myKey, movie)
print('Movie:',res['Search'][0]['Title'])
print('Year:',res['Search'][0]['Year'])
print('Type:',res['Search'][0]['Type'])

import requests

def getMovie(myKey, movie):
    parameters = {'s':movie, 'type':'movie'}
    res = requests.get(myKey, parameters)
    return eval(res.content.decode('utf-8'))

myKey = 'http://www.omdbapi.com/?i=tt3896198&apikey=841ba8d4'
print(myKey)
movie = 'lion king'
res = getMovie(myKey, movie)
print(res['Search'])
print('Movie:',res['Search'][1]['Title'])
print('Year:',res['Search'][1]['Year'])
print('Type:',res['Search'][1]['Type'])