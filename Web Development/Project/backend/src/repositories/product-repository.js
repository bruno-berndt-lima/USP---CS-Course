'use strict';

const mongoose = require('mongoose');
const Product = mongoose.model('Product');

exports.get = () => {
    return Product.find({}, 'brand model price sizes sold description slug active image');
}

exports.getCount = query => {
    return Product.countDocuments(query).exec();
}

exports.getPage = (query, limit, startIndex) => {
    return Product.find(query).limit(limit).skip(startIndex).exec();
}

exports.getBySlug = slug => {
    return Product.findOne({
        slug: slug,
        active: true
     }, 'brand model price sizes sold description slug image');
}

exports.getByTag = tag => {
    return Product.find({
        tags: tag,
        active: true
     }, 'brand model price sizes sold description slug image');
}

exports.getByID = id => {
    return Product.findById(id, 'brand model price sizes sold description slug image');
}

exports.create = data => {
    const product = new Product(data);
    return product.save();
}

exports.update = (id, data) => {
    return Product.findByIdAndUpdate(id, {
        $set: {
           brand: data.brand,
           model: data.model,
           slug: data.slug,
           sizes: data.sizes,
           description: data.description,
           price: data.price,
           active: data.active,
           sold: data.sold
        }
     });
}

exports.delete = id => {
    return Product.findByIdAndDelete(id);
}