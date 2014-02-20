#!/bin/ruby

require 'pry'
require 'faraday'

APIKEY=ENV["PAPI_KEY"]
USERID=ENV["PUSER_ID"]

response = Faraday.post("https://api.pushover.net/1/messages.json", {:token=>APIKEY, :user => USERID, :message => ARGV[0]})
puts "Message sent successfully" if response.status == 200


