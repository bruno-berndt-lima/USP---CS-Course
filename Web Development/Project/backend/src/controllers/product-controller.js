'use strict';

const repository = require("../repositories/product-repository");

exports.get = async (req, res, next) => {
   try {
      const data = await repository.get();
      res.status(200).send(data);
   } catch (error) {
      res.status(400).send(error);
   }
}

exports.getPage = async (req, res, next) => {
   const page = parseInt(req.query.page) || 1;
   const limit = 12;

   const startIndex = (page - 1) * limit
   const endIndex = page * limit
   
   const results = {}

   const query = {$or: [
      {
         model: {
            $regex: req.query.model || "",
            $options: 'i'
         },
      },
      {
         brand: {
            $regex: req.query.brand || "",
            $options: 'i'
         }
      }
   ]};

   const count = await repository.getCount(query);
   
   if (endIndex < count) {
      results.next = {
        page: page + 1,
        limit: limit
      }
   }
   
   if (startIndex > 0) {
      results.previous = {
        page: page - 1,
        limit: limit
      }
   }

   try {
      // const data = await repository.getPage();
      results.results = await repository.getPage(query, limit, startIndex);
      
      res.status(200).send(results);
   } catch (error) {
      res.status(400).send(error);
   }   
}

exports.getRelated = async (req, res, next) => {
   const query = {
         brand: {
            $regex: req.query.brand || "",
            $options: 'i'
         }
   };

   try {
      const data = await repository.getPage(query, 4, 0);
      
      res.status(200).send(data);
   } catch (error) {
      res.status(400).send(error);
   }   
}

exports.getBySlug = async (req, res, next) => {
   try {
      const data = await repository.getBySlug(req.params.slug);

      res.status(200).send(data);
   } catch (error) {
      res.status(400).send(error);
   }
}

exports.getByID = async (req, res, next) => {
   try {
      const data = await repository.getByID(req.params.id);

      res.status(200).send(data);
   } catch (error) {
      res.status(400).send(error);
   }
}

exports.post = async (req, res, next) => {
   try {
      const data = await repository.create(req.body);

      res.status(201).send({
         message: 'Produto cadastrado com sucesso',
         data: data
      });
   } catch (error) {
      res.status(400).send({
         message: 'Falha ao cadastrar produto',
         data: error
      });
   }
};

exports.put = async (req, res, next) => {
   try {
      const data = await repository.update(req.params.id, req.body);

      res.status(200).send({
         message: 'Produto atualizado com sucesso',
         data: data
      });
   } catch (error) {
      res.status(400).send({
         message: "Falha ao atualizar produto",
         data: error
      })
   }
   // const id = req.params.id;
   // res.status(201).send({ id: id, item: req.body });
};

exports.delete = async (req, res, next) => {
   try {
      const data = await repository.delete(req.body.id);

      res.status(200).send({
         message: 'Produto removido com sucesso',
         data: data
      })
   } catch (error) {
      res.status(400).send({
         message: 'Falha ao remover produto',
         data: error
      })
   }
};