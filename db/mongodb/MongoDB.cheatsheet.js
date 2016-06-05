// --------------------------cursor --------------------------
var c = db.testData.find()
while (c.hasNext()) printjson(c.next())
while (myCursor.hasNext()) {  print(tojson(myCursor.next())); }
myCursor.forEach(printjson);

//cursor index
var c = db.testData.find()
printjson( c [ 4 ] )
var myCursor = db.inventory.find( { type: 'food' } );
var documentArray = myCursor.toArray();
var myDocument = documentArray[3];

var myCursor = db.inventory.find().addOption(DBQuery.Option.noTimeout);
var myCursor = db.inventory.find();
var myFirstDocument = myCursor.hasNext() ? myCursor.next() : null;
myCursor.objsLeftInBatch();				                            //check how many remain in the batch
db.serverStatus().metrics.cursor;


// -------------------------- Query --------------------------
db.testData.find( { x : 18 } );								        // return cursor
db.testData.findOne( { x : 18 } );							        // return document
db.testData.find().limit(3);

db.users.find( { age: { $gt: 18 } }, { name: 1, address: 1 } ).limit(5);
// equals to: select _id, name, address from users where age > 18 limit 5
db.users.find( { age: { $gt: 18 } } ).sort( {age : 1} )

db.inventory.find( { type: { $in: [ 'food', 'snacks' ] } } );  	    // in operator
db.inventory.find( { type: 'food', price: { $lt: 9.95 } } );	    //comparison operator
db.inventory.find(
   {
     type: 'food',													//and operator
     $or: [ { qty: { $gt: 100 } }, { price: { $lt: 9.95 } } ]  		//or operator
   }
);
db.inventory.find( { 'producer.company': 'ABC123' } )	//embeded document query
db.inventory.find( { 'ratings.0': 5 } )	;								//ratings[0] = 5
db.inventory.find( { ratings: { $elemMatch: { $gt: 5, $lt: 9 } } } );	//ratings contain 5<x<9
db.inventory.find( { ratings: { $gt: 5, $lt: 9 } } );				    // element match x>5 or x<9 or 5<x<9


// -------------------------- Projection ----------------------------------
db.records.find( { "user_id": { $lt: 42} }, { history: 0} );            //exclude history field
db.records.find( { "user_id": { $lt: 42} }, { "_id": 0, "name": 1 , "email": 1 } );


// -------------------------- Insert --------------------------
db.users.insert(
   {
      name: "sue",
      age: 26,
      status: "A"
   }
);
db.inventory.update(
 { type: "book", item : "journal" },
 { $set : { qty: 10 } },
 { upsert : true }					//upsert
);
db.inventory.save( { type: "book", item: "notebook", qty: 40 } );

// -------------------------- Update --------------------------
db.users.update(
   { age: { $gt: 18 } },
   { $set: { status: "A" } },
   { multi: true }				                                //update all document match query
);
db.inventory.update(
   { type : "book" },
   { $inc : { qty : -1 } },		                                //increase qty
   { multi: true }
);
db.inventory.save(
   {
     _id: 10,						                            //replace document with _id=10
     type: "misc",
     item: "placard"
   }
);
db.students.update(		                                        //update array only keep 3 records
	{ _id: 1 },
	{
        $push: {
            scores: {
                $each : [		                                //scores array insert 2 records
                    { attempt: 3, score: 7 },
                    { attempt: 4, score: 4 }
                ],
                $sort: { score: 1 },	                        //scores array sort by score asc
                $slice: -3				                        //keep last 3 elements in array
            }
        }
	}
);

// -------------------------- Remove --------------------------
db.users.remove(
   { status: "D" }
);
db.inventory.remove( { type : "food" }, 1 );		            //remove only one doc
db.inventory.remove({});		                                //remove all docs but not indicator
db.inventory.drop();				                            //remove all include indicator
db.people.findAndModify(	                                    //query then modify
   {
     query: { state: "active" },
     sort: { rating: 1 },
     remove: true
   }
);


// -------------------------- Write concern --------------------------
//unacknowledged
//acknowledged
//journaled
//replica acknowledged

// -------------------------- Hierarchy --------------------------
//Database  > Collection > document > field


// -------------------------- Document Structure --------------------------
//references
//	in case of document append to relocate
//embedded documents
//	better atomic modification


// -------------------------- Join --------------------------
original_id = ObjectId();
db.places.insert({
    "_id": original_id,
    "name": "Broadway Center",
    "url": "bc.example.net"
});
db.people.insert({
    "name": "Erin",
    "places_id": original_id,		                            // refer to places.original_id
    "url":  "bc.example.net/Erin"
});


// -------------------------- Aggregation --------------------------
db.orders.aggregate([
	{ $match : { status : "A"} },
	{ $group :  { _id : "$cust_id", total : { $sum : "$amount"}} }
]);

db.records.count( { a: 1 } );
db.records.distinct( "b" );			//distinct on field b
db.records.group( {
   key: { a: 1 },
   cond: { a: { $lt: 3 } },
   reduce: function(cur, result) { result.count += cur.count },
   initial: { count: 0 }
});

var aggregator = {
    $group: {
        _id: "$_id.state",
	    biggestCity:  { $last: "$_id.city" },			//select last element in array
	    biggestPop:   { $last: "$pop" },
	    smallestCity: { $first: "$_id.city" },			//select first element in array
	    smallestPop:  { $first: "$pop" }
    }
};

// -------------------------- Map & Reduce --------------------------
var mapFunction1 = function() { emit(this.cust_id, this.price);  };			        //use this refer this document
var reduceFunction1 = function(keyCustId, valuesPrices) { return Array.sum(valuesPrices); };
db.orders.mapReduce(mapFunction1, reduceFunction1, { out: "map_reduce_example" });

// -------------------------- Index --------------------------
db.inventory.ensureIndex( { type: 1 } );
db.users.ensureIndex( { user_id: 1, age: -1 } );							        //-1 desc
db.people.ensureIndex( { "address.zipcode": 1 } );						            //embedded field index
db.members.ensureIndex( { "user_id": 1 }, { unique: true } );		                //force unique
db.people.ensureIndex( { zipcode: 1}, {background: true, sparse: true } );		    //background index constructor
db.products.ensureIndex( { item: 1, quantity: -1 } , { name: "inventory" } );		//named index
