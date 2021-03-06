const express = require('express');
const router = express.Router();
const tilitapahtumat = require('../models/tilitapahtumat_model');
let ttSivu = 1;
let rivit = 10;


router.get('/get/:id/:ttSivu/:rivit',
function(request, response) {
  if (request.params.ttSivu) {
     
    tilitapahtumat.get(request.params.id, request.params.ttSivu, request.params.rivit, function(err, dbResult) {
      if (err) {
        response.json(err);
      } else {
        response.json(dbResult);
      }
    });
  }
}); 

router.get('/:id?',
 function(request, response) {
  if (request.params.id) {
    tilitapahtumat.getById(request.params.id, function(err, dbResult) {
      if (err) {
        response.json(err);
      } else {
        response.json(dbResult);
      }
    });
  } else {
    tilitapahtumat.getAll(function(err, dbResult) {
      if (err) {
        response.json(err);
      } else {
        response.json(dbResult);
      }
    });
  }
});


router.post('/', 
function(request, response) {
  tilitapahtumat.add(request.body, function(err, dbResult) {
    if (err) {
      response.json(err);
    } else {
      response.json(request.body);
    }
  });
});


router.delete('/:id', 
function(request, response) {
  tilitapahtumat.delete(request.params.id, function(err, dbResult) {
    if (err) {
      response.json(err);
    } else {
      response.json(dbResult);
    }
  });
});


router.put('/:id', 
function(request, response) {
  tilitapahtumat.update(request.params.id, request.body, function(err, dbResult) {
    if (err) {
      response.json(err);
    } else {
      response.json(dbResult);
    }
  });
});

router.post('/debit',
function(request,response) {
  tilitapahtumat.debit(request.body, function(err, dbResult) {
    if (err) {
      response.json(err);
    } else {
      response.json(dbResult.affectedRows);
    }
  });
});

module.exports = router;