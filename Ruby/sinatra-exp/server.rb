require 'rubygems'
require 'sinatra'
require 'rack'
require 'rack/contrib'
require 'pry'

set :bind, '127.0.0.1'
set :public_dir, 'public'

$status_header = "1"
5.times{ $status_header << ",1"}
4.times{ $status_header << ",0"} 


p $status_header

@@request_number = 0

get "/fetch" do
    images_hash = request.env["HTTP_CHECK_RESOURCE"].split("::")
    hsh = {}
    images_hash.map{|i| hsh[i.split(" ")[0]] = i.split(" ")[1]}
    response["resource-status"] = $status_header
end

get '/fetchB/:image_name' do
    sh = $status_header.split(',')
    if sh[@@request_number] == "0"
        @@request_number += 1
        return 304
    end
    @@request_number += 1
    p "REQUEST NUMBER #{@@request_number}"
    send_file File.join(settings.public_folder, params["image_name"])
end
