open Webapi;

module Error = {
  type t('e) = Js.t('e);
};

module Database = {
  type t;
  module rec Reference: {
    type t;
    [@bs.get] external key : t => Js.Nullable.t(string) = "";
    [@bs.get] external parent : t => Js.Nullable.t(t) = "";
    [@bs.get] external root : t => t = "";
    [@bs.send] external child : (t, ~path: string) => t = "";
    type cb = DataSnapshot.t => unit;
    [@bs.send]
    external once :
      (
        t,
        ~eventType: string,
        ~successCallback: cb=?,
        ~failureCallbackOrContext: Error.t('e) => unit=?,
        unit
      ) =>
      Js.Promise.t(DataSnapshot.t) =
      "";
    [@bs.send]
    external on :
      (
        t,
        ~eventType: string,
        ~callback: cb,
        ~cancelCallback: Error.t('e) => unit=?,
        unit
      ) =>
      cb =
      "";
    [@bs.send]
    external off : (t, ~eventType: string, ~callback: cb=?, unit) => unit = "";
    [@bs.send]
    external set :
      (
        t,
        ~value: 'a,
        ~onComplete: Js.Nullable.t(Error.t('e)) => unit=?,
        unit
      ) =>
      Js.Promise.t(unit) =
      "";
    [@bs.send]
    external update :
      (
        t,
        ~value: 'a,
        ~onComplete: Js.Nullable.t(Error.t('e)) => unit=?,
        unit
      ) =>
      Js.Promise.t(unit) =
      "";
    [@bs.send]
    external push :
      (
        t,
        ~value: 'a=?,
        ~onComplete: Js.Nullable.t(Error.t('e)) => unit=?,
        unit
      ) =>
      t =
      "";
  } = Reference
  and DataSnapshot: {
    type t;
    [@bs.get] external key : t => Js.Null.t(string) = "";
    [@bs.get] external ref : t => Reference.t = "";
    [@bs.send] external child : (t, ~path: string) => t = "";
    [@bs.send] external exists : t => bool = "";
    [@bs.send] external exportVal : t => Js.Json.t = "";
    [@bs.send] external foreach : (t, t => bool) => bool = "forEach";
    /*external getPriority*/
    [@bs.send] external hasChild : (t, ~path: string) => bool = "";
    [@bs.send] external hasChildren : t => bool = "";
    [@bs.send] external numChildren : t => int = "";
    [@bs.send] external toJson : t => Js.Json.t = "toJSON";
    [@bs.send] external val_ : t => Js.Json.t = "val";
  } = DataSnapshot;
  module OnDisconnect = {
    type t;
    [@bs.send]
    external cancel :
      (t, ~onComplete: Js.Nullable.t(Error.t('e)) => unit=?) =>
      Js.Promise.t(unit) =
      "";
    [@bs.send]
    external remove :
      (t, ~onComplete: Js.Nullable.t(Error.t('e)) => unit=?) =>
      Js.Promise.t(unit) =
      "";
    [@bs.send]
    external set :
      (t, Js.Json.t, ~onComplete: Js.Nullable.t(Error.t('e)) => unit=?) =>
      Js.Promise.t(unit) =
      "";
    /*external setWithPriority*/
    [@bs.send]
    external update :
      (t, Js.Json.t, ~onComplete: Js.Nullable.t(Error.t('e)) => unit=?) =>
      Js.Promise.t(unit) =
      "";
  };
  module ThenableReference = {
    type t;
  };
  module Query = {
    type t;
  };
  [@bs.send] external goOffline : t => unit = "";
  [@bs.send] external goOnline : t => unit = "";
  [@bs.send] external ref : (t, ~path: string=?, unit) => Reference.t = "";
  [@bs.send] external refFromURL : (t, ~url: string) => Reference.t = "";
  [@bs.val] [@bs.module "firebase"] [@bs.scope ("database", "ServerValue")]
  external serverTimestamp : Js.Null.t(string) = "TIMESTAMP";
};

module Storage = {
  type t;
  module UploadTask = {
    type t;
  };
  module Reference = {
    type t;
    [@bs.get] external bucket : t => string = "";
    [@bs.get] external fullPath : t => string = "";
    [@bs.get] external name : t => string = "";
    [@bs.get] external parent : t => option(t) = "";
    [@bs.get] external root : t => t = "";
    [@bs.send] external path : (t, ~path: string) => t = "";
    [@bs.send]
    external put :
      (t, ~data: File.t, ~metadata: Js.t('a)=?, unit) =>
      Js.Promise.t(UploadTask.t) =
      "";
    [@bs.send] external delete : t => Js.Promise.t(unit) = "";
    [@bs.send] external getDownloadURL : t => Js.Promise.t(string) = "";
  };
  [@bs.send] external ref : (t, ~path: string=?, unit) => Reference.t = "";
};

module Auth = {
  type t;
  module User = {
    type t;
    type profile = {
      .
      "displayName": Js.Nullable.t(string),
      "photoURL": Js.Nullable.t(string),
    };
    [@bs.get] external displayName : t => string = "";
    [@bs.get] external email : t => Js.Nullable.t(string) = "";
    [@bs.get] external emailVerified : t => bool = "";
    [@bs.get] external isAnonymous : t => bool = "";
    [@bs.get] external phoneNumber : t => Js.Nullable.t(string) = "";
    [@bs.get] external photoUrl : t => Js.Nullable.t(string) = "";
    [@bs.get] external uid : t => string = "";
    [@bs.send]
    external updateProfile : (t, ~profile: profile) => Js.Promise.t(unit) =
      "";
    [@bs.send]
    external getIdToken : t => Js.Promise.t(Js.Nullable.t(string)) = "";
  };
  module AuthCredential = {
    type t;
  };
  [@bs.get] external currentUser : t => Js.Null.t(User.t) = "";
  [@bs.send]
  external onAuthStateChanged :
    (
      t,
      ~nextOrObserver: Js.Null.t(User.t) => unit,
      ~error: Error.t('e) => unit=?,
      ~completed: unit => unit=?
    ) =>
    unit =
    "";
  [@bs.send]
  external signInAnonymously : (t, unit) => Js.Promise.t(User.t) = "";
  [@bs.send]
  external signInWithCredential :
    (t, ~credential: AuthCredential.t) => Js.Promise.t(User.t) =
    "";
  [@bs.send]
  external signInWithCustomToken : (t, ~token: string) => Js.Promise.t(User.t) =
    "";
  [@bs.send] external signOut : t => Js.Promise.t(unit) = "";
};

module App = {
  type t;
  [@bs.send] external auth : t => Auth.t = "";
  [@bs.send] external database : t => Database.t = "";
  /*external delete*/
  /*external messaging*/
  [@bs.send] external storage : t => Storage.t = "";
  [@bs.get] external options : t => Js.t('a) = "";
};

type options = {
  .
  "apiKey": string,
  "authDomain": string,
  "databaseURL": string,
  "projectId": string,
  "storageBucket": string,
  "messagingSenderId": string,
};

[@bs.module "firebase"]
external initializeApp : (~options: options) => App.t = "";

[@bs.module "firebase"] external app : (~name: string=?) => App.t = "";

[@bs.module "firebase"] external apps : array(App.t) = "";