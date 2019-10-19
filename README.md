# BuckleScript bindings for firebase
Add type for in reason to google's firebase api documented
[here](https://firebase.google.com/docs/reference/js/).
## Install
yarn add (git url)
add to your bsconfig.json
```json
  "bs-dependencies": [
    "bs-firebase"
  ],
```

## Example

```reason
let options =
   {
	"apiKey": "...",
	"authDomain": "...",
	"databaseURL": "...",
	"storageBucket": "...",
	"messagingSenderId": "..."
   };

let app = BsFirebase.ReasonFirebase.initializeApp(options);

let db = BsFirebase.ReasonFirebase.App.database(app);

BsFirebase.ReasonFirebase.Database.Reference.once(
      BsFirebase.ReasonFirebase.Database.ref(db, ~path="ticket", ()),
      ~eventType="value",
      ()
    )
    |> Js.Promise.then_(
      (teamDomain) => BsFirebase.ReasonFirebase.Database.DataSnapshot.val_(teamDomain)
        |> (ticket) => parseTicket(ticket)
        |> (ticketJson) => Js.log(ticketJson) //here you got a record of ticket type
        |> Js.Promise.resolve
    );

type ticket = {
  id: int,
  name: string
};

type state =  {
  ticket : ticket
};

let parseTicket = (json): ticket =>
  Json.Decode.{ //Json.Decode is from module https://github.com/reasonml-community/bs-json
      id: json |> field("id",int),
      name: json |> field("name", string)
  };
```
