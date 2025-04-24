'use strict';

const repository = require("../repositories/login-repository");

exports.login = async (req, res, next) => {
   try {
      const data = await repository.login(req.body);

      res.status(200).send(data);
   } catch (error) {
      res.status(400).send(error);
   }
}

exports.getByEmail = async (req, res, next) => {
    try {
       const data = await repository.getEmail(req.params.email);
 
       res.status(200).send(data);
    } catch (error) {
       res.status(400).send(error);
    }
}