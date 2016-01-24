var http = require('http');

var server = http.createServer(function(req, res){
  res.writeHead(200, {"Content-Type": "text/html"});
  res.end(`
          <!DOCTYPE html>
          <html>
          <head>HTML response</head>
          <body>
            <h1> ${req.url}</h1>
            <h1> ${req.method}</h1>
            <h1> ${req.headers}</h1>
          </body>
          </html>
          `);
});

server.listen(3000);
console.log("Server listening on 3000");
