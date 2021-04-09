import requests

def getMovie(myKey, movie):
    parameters = {'s':movie, 'type':'movie'}
    res = requests.get(myKey, parameters)
    return eval(res.content.decode('utf-8'))

myKey = 'http://www.omdbapi.com/?i=tt3896198&apikey=841ba8d4'
print(myKey)
movie = 'avengers'
res = getMovie(myKey, movie)
print(res['Search'])
print('Movie:',res['Search'][1]['Title'])
print('Year:',res['Search'][1]['Year'])
print('Type:',res['Search'][1]['Type'])