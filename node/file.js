var fs = require('fs');
var path = require('path');

var content = fs.readFileSync('./sayings.md', 'UTF-8');
console.log(content);

// Without text encoding ==> binary
var content = fs.readFileSync('./sayings.md');
console.log(content);
// <Buffer 74 68 69 73 20 69 73 20 63 6f 6f 6c 0a 6f 6b 61 79 20 6a 75 73 74 20 61 20 66 69 6c 65 0a 77 69 74 68 20 73 6f 6d 65 20 72 61 6e 64 6f 6d 20 74 65 78 ... >


// Asyn read
fs.readFile('./sayings.md', 'UTF-8', function(err, stdout) {
  if (err) {
    throw err;
  }
  console.log(stdout)
});


// dir
fs.readdir('.', function(err, files) {

  if (err) {
    throw err;
  }

  files.forEach(function(fileName) {
    var file = path.join(__dirname, fileName);
    var stats = fs.statSync(file);
    console.log(`File: ${file}, Stats: ${stats}`);

  });
});
