module Port = {
  type t;
  [@bs.send] [@bs.scope "onMessage"] external addListener: (Messages.portMessages => unit) => unit = "addListener";
  [@bs.send] external postMessage: Messages.portMessages => unit = "postMessage";
};

module OnMessage = {
  [@bs.val] [@bs.scope ("chrome", "runtime", "onMessage")]
  external addListener: Chrome_Types.onMessageListener => unit = "addListener";
};

type t;
[@bs.val] [@bs.scope ("chrome", "runtime")] external runtimeId: string = "id";
[@bs.val] [@bs.scope "chrome"] external runtime: t = "runtime";
[@bs.val] [@bs.scope ("chrome", "runtime")] external getURL: string => string = "getURL";

type connectInfo = {
  name: string,
  includeTlsChannelId: option(bool),
};
[@bs.send] [@bs.scope "chrome"] external connect1: (t, connectInfo) => Port.t = "connect";
[@bs.val] [@bs.scope ("chrome", "runtime")]
external sendMessage: (Messages.request, Messages.response => unit) => unit = "sendMessage";

type lastError = {message: string};
[@bs.val] [@bs.scope ("chrome", "runtime")] external lastError: option(lastError) = "lastError";