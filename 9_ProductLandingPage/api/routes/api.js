var express = require("express");
var router = express.Router();
const fs = require('fs');

router.get("/product/:title", function(req, res) {
    var title = req.params.title;
    
    if(title == 'init'){
        res.send(getProductData()["init"]);
    } else {
        res.send(getProductData()["slides"][title]);
    }

});

function getProductData(){
    let rawdata = fs.readFileSync('./storage/productData.json');
    let data = JSON.parse(rawdata);
    return data
}

module.exports = router;