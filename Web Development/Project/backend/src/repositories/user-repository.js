'use strict';

const mongoose = require('mongoose');
const User = mongoose.model('User');

exports.get = () => {
    return User.find({}, 'name cpf email phones address admin cart');
}

exports.create = data => {
    const user = new User(data);
    return user.save();
}

exports.update = (id, data) => {
    return User.findByIdAndUpdate(id, {
        $set: {
           cart: data.cart,
           admin: data.admin
        }
    });
}

exports.delete = id => {
    return User.findByIdAndDelete(id);
}