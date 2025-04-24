'use strict';

const mongoose = require('mongoose');
const Product = mongoose.model('Product');

exports.get = () => {
    return Product.find({}, 'name price quantity description slug');
}

exports.getBySlug = slug => {
    return Product.findOne({
        slug: slug,
     }, 'name price quantity description slug');
}

exports.getByID = id => {
    return Product.findById(id, 'name price quantity description slug');
}

exports.create = data => {
    const product = new Product(data);
    return product.save();
}

exports.update = (id, data) => {
    return Product.findByIdAndUpdate(id, {
        $set: {
           name: data.name,
           slug: data.slug,
           description: data.description,
           price: data.price,
           quantity: data.quantity
        }
     });
}

exports.delete = id => {
    return Product.findByIdAndDelete(id);
}