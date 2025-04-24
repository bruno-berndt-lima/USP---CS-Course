'use strict';

const guid = require("guid");
const repository = require("../repositories/order-repository");

exports.get = async (req, res, next) => {
    try {
       const data = await repository.get();
 
       res.status(200).send(data);
    } catch (error) {
       res.status(400).send(e);
    }
}

exports.post = async (req, res, next) => {
    try {
        const data = await repository.create({
            user: req.body.user,
            number: guid.raw().substring(0, 6),
            items: req.body.items
        });

        res.status(201).send({
            message: 'Pedido cadastrado com sucesso',
            data: data
        });
    } catch (error) {
        res.status(400).send({
            message: 'Falha ao cadastrar pedido',
            data: error
        });
    }
};