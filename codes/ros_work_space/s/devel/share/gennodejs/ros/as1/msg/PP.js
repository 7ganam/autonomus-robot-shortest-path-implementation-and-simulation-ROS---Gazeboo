// Auto-generated. Do not edit!

// (in-package as1.msg)


"use strict";

let _serializer = require('../base_serialize.js');
let _deserializer = require('../base_deserialize.js');
let _finder = require('../find.js');

//-----------------------------------------------------------

class PP {
  constructor() {
    this.velx = 0.0;
    this.vely = 0.0;
    this.posx = 0.0;
    this.posy = 0.0;
  }

  static serialize(obj, bufferInfo) {
    // Serializes a message object of type PP
    // Serialize message field [velx]
    bufferInfo = _serializer.float64(obj.velx, bufferInfo);
    // Serialize message field [vely]
    bufferInfo = _serializer.float64(obj.vely, bufferInfo);
    // Serialize message field [posx]
    bufferInfo = _serializer.float64(obj.posx, bufferInfo);
    // Serialize message field [posy]
    bufferInfo = _serializer.float64(obj.posy, bufferInfo);
    return bufferInfo;
  }

  static deserialize(buffer) {
    //deserializes a message object of type PP
    let tmp;
    let len;
    let data = new PP();
    // Deserialize message field [velx]
    tmp = _deserializer.float64(buffer);
    data.velx = tmp.data;
    buffer = tmp.buffer;
    // Deserialize message field [vely]
    tmp = _deserializer.float64(buffer);
    data.vely = tmp.data;
    buffer = tmp.buffer;
    // Deserialize message field [posx]
    tmp = _deserializer.float64(buffer);
    data.posx = tmp.data;
    buffer = tmp.buffer;
    // Deserialize message field [posy]
    tmp = _deserializer.float64(buffer);
    data.posy = tmp.data;
    buffer = tmp.buffer;
    return {
      data: data,
      buffer: buffer
    }
  }

  static datatype() {
    // Returns string type for a message object
    return 'as1/PP';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'e6be4b315e1490f51ec3a3cda103c9a9';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    float64 velx
    float64 vely
    float64 posx
    float64 posy
    
    
    `;
  }

};

module.exports = PP;
