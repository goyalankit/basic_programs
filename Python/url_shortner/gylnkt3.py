import cgi
from google.appengine.ext import db
from google.appengine.ext import webapp
from google.appengine.ext.webapp.util import run_wsgi_app
from google.appengine.ext.webapp import template
import wsgiref.handlers
import re

class UrlMap(db.Model):
	s_url = db.StringProperty(required = True)
	url = db.StringProperty(required = True)

class Redirect(webapp.RequestHandler):
	def get(self):
		results = db.GqlQuery("SELECT * FROM UrlMap WHERE s_url = :1	", self.request.path).fetch(1)
		if results:
			for obj in results:
				self.redirect(obj.url)

class Mainpage(webapp.RequestHandler):
	def get(self):
		self.response.out.write(template.render('index.html', {}))

class UrlShortener(webapp.RequestHandler):
	def post(self):
		value = self.request.get("url")
                hint = self.request.get("hint")
		match = re.search(r'http[s|]*://', value)
                if not hint:
                        self.response.out.write("""<html><body>Try some other hint <a href="http://gylnkt.me">go back</a></body></html>""")
                        return

		if match:
			pass
		else:
			value = "http://" + value
		results = db.GqlQuery("SELECT * FROM UrlMap WHERE url = :1	", value).fetch(1)
		hint_taken = db.GqlQuery("SELECT * FROM UrlMap WHERE s_url = :1	", ('/'+hint)).fetch(1)
		if results:
			for obj in results:
				self.response.out.write("""<html><body><a href=%s>http://gylnkt.me/%s</a></body></html>""" %(obj.url,obj.s_url))
                elif hint_taken:
                        self.response.out.write("""<html><body>Try some other hint <a href="http://gylnkt.me">go back</a></body></html>""")

		else:
			url_map = UrlMap(s_url = '/'+hint, url = value)
			url_map.put()
			self.response.out.write("""<html><body><a href=%s>http://gylnkt.me/%s</a></body></html>""" %(value,hint))

application = webapp.WSGIApplication([('/', Mainpage), ('/s_url', UrlShortener), ('/[a-zA-z0-9-]*', Redirect)], debug=True)

def main():
	run_wsgi_app(application)
if __name__ == "__main__":
	main()
