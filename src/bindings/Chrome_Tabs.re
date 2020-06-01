type scriptCode = {code: string};
type scriptFile = {file: string};
type executeScriptResult;
[@bs.val] [@bs.scope ("chrome", "tabs")]
external executeScriptFile: (scriptFile, executeScriptResult => unit) => unit = "executeScript";
let executeScriptFile = (file: string, cb) => {
  let script: scriptFile = {file: file};
  executeScriptFile(script, cb);
};

[@bs.val] [@bs.scope ("chrome", "tabs")]
external executeScriptCode: (scriptCode, unit => unit) => unit = "executeScript";
let executeScriptCode = (code: string, cb) => {
  let script: scriptCode = {code: code};
  executeScriptCode(script, cb);
};

type queryInfo;
[@bs.obj]
external makeQueryInfo:
  (
    ~active: bool=?,
    ~pinned: bool=?,
    ~audiable: bool=?,
    ~muted: bool=?,
    ~highlighted: bool=?,
    ~discarded: bool=?,
    ~autoDiscardable: bool=?,
    ~currentWindow: bool=?,
    ~lastFocusedWindow: bool=?,
    ~status: bool=?,
    ~title: string=?,
    ~url: string=?, //note(itay): This can also be an array of strings, ignoring for now
    ~windowId: string=?,
    ~windowType: string=?,
    ~index: int=?,
    unit
  ) =>
  queryInfo;
type queryCallback = array(Chrome_Types.tab) => unit;
[@bs.val] [@bs.scope ("chrome", "tabs")] external query: (queryInfo, queryCallback) => unit = "query";

type sendMessageOptions = {frameId: int};
[@bs.val] [@bs.scope ("chrome", "tabs")]
external sendMessage: (int, Messages.request, option(Messages.response) => unit) => unit = "sendMessage";

type createTabOptions = {
  windowId: option(int),
  index: option(int),
  url: option(string),
  active: option(bool),
  pinned: option(bool),
  openerTabId: option(int),
};

[@bs.val] [@bs.scope ("chrome", "tabs")]
external create: (createTabOptions, option(Chrome_Types.tab => unit)) => unit = "create";
let makeCreateTabOptions =
    (~windowId=?, ~index=?, ~url=?, ~openerTabId=?, ~active=Some(true), ~pinned=Some(false), ()) => {
  {windowId, index, url, openerTabId, active, pinned};
};

module rec CaptureFormat: {
  type t = pri string;

  [@bs.inline "jpeg"]
  let jpeg: t;
  [@bs.inline "png"]
  let png: t;
} = CaptureFormat;

type captureVisibleTabOptions = {
  format: CaptureFormat.t,
  quality: int,
};
[@bs.val] [@bs.scope ("chrome", "tabs")]
external captureVisibleTab: (~windowId: int=?, ~options: captureVisibleTabOptions=?, string => unit) => unit =
  "captureVisibleTab";

let sendMessage = (tabId, message, cb) => {
  sendMessage(tabId, message, response => {
    switch (response) {
    | Some(res) => cb(Ok(res))
    | None => cb(Error(Chrome_Runtime.lastError->Belt.Option.getWithDefault({message: ""})))
    }
  });
};