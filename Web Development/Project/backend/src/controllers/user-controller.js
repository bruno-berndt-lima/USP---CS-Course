'use strict';

const repository = require("../repositories/user-repository");

exports.get = async (req, res, next) => {
    try {
       const data = await repository.get();
 
       res.status(200).send(data);
    } catch (error) {
       res.status(400).send(error);
    }
}

exports.post = async (req, res, next) => {
    try {
        const data = await repository.create(req.body);

        res.status(201).send({
            message: 'Cliente cadastrado com sucesso',
            data: data
        });
    } catch (error) {
        res.status(400).send({
            message: 'Falha ao cadastrar cliente',
            data: error
        });
    }
};

exports.put = async (req, res, next) => {
    try {
        const data = await repository.update(req.params.id, req.body);
  
        res.status(200).send({
           message: 'Cliente atualizado com sucesso',
           data: data
        });
    } catch (error) {
        res.status(400).send({
            message: "Falha ao atualizar cliente",
            data: error
        })
    }
}

exports.delete = async (req, res, next) => {
    try {
       const data = await repository.delete(req.body.id);
 
       res.status(200).send({
          message: 'User removido com sucesso',
          data: data
       })
    } catch (error) {
       res.status(400).send({
          message: 'Falha ao remover user',
          data: error
       })
    }
 };