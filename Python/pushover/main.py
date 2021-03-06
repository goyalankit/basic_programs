from flask import Flask
from flask import request
import os
import urllib
import urllib2

app = Flask(__name__)

@app.route("/")
def hello():
    return "Hello World!"

@app.route("/send")
def send():
    if request.args.get('message') is not None:
        print request.args
        values = generate_values(request.args)
        if values['message'] is None: return """Must provide 'message' parameter
        at least. Other possible options include 'title', 'priority(-1,1)'"""
        print values
        make_a_request(values)
        return "sending message"
    else:
        return "message arg not present"

def make_a_request(values):
    url    = "https://api.pushover.net/1/messages.json"
    data   = urllib.urlencode(values)
    req    = urllib2.Request(url, data)
    response = urllib2.urlopen(req)
    if response.getcode() == 200:
        return "Message sent successfully."
    else:
        return "Oops! something went wrong."


def generate_values(params):
    values = { 'token' : os.environ['PAPIKEY'], 'user' : os.environ['USERID'] }
    if params['message'] is None : return
    values['message']  = params.get( 'message' )
    values['title']    = params.get( 'title' ) if params.get( 'title' ) is not None else 'web hook message'
    values['priority'] = int(params.get( 'priority' )) if params.get( 'priority' ) is not None else 0
    values['sound'] = 'gamelan'
    return values

@app.errorhandler(404)
def page_not_found(e):
    """Return a custom 404 error."""
    return 'Sorry, Nothing at this URL.', 404

if __name__ == "__main__":
    app.debug = True
    app.run()

