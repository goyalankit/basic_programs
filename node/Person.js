var EventEmitter = require('events').EventEmitter;
var util = require('util');
var Person = function(name) {
  this.name = name
};

// Person prototype inherits EventEmitter
util.inherits(Person, EventEmitter);

module.exports = Person; // returns on require
