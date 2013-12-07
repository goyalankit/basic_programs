require 'rubygems'
require 'sinatra'
require 'rack'
require 'rack/contrib'
require 'pry'

cnf = YAML::load_file(File.join(File.dirname(File.expand_path(__FILE__)), 'config.yml')

not_found do
    requested_path = request.env["REQUEST_PATH"]
    response.headers["foo"] = "bar"
    nil
end
