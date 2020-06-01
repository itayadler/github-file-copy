type mutedInfo = {
  muted: bool,
  reason: option(string),
  extensionId: option(string),
};
type tab = {
  id: option(int),
  index: int,
  windowId: int,
  openerTabId: option(int),
  highlighted: bool,
  active: bool,
  pinned: bool,
  audible: option(bool),
  discarded: bool,
  autoDiscardable: bool,
  mutedInfo: option(mutedInfo),
  url: option(string),
  pendingUrl: option(string),
  title: option(string),
  favIconUrl: option(string),
  status: option(string),
  incognito: bool,
  width: option(int),
  height: option(int),
  sessionId: option(string),
};
type messageSender = {
  tab: option(tab),
  frameId: option(int),
  id: option(string),
  url: option(string),
  nativeApplication: option(string),
  tlsChannelId: option(string),
  origin: option(string),
};
type sendResponse = Messages.response => unit;
type onMessageListener =
  (Messages.request, messageSender, sendResponse) => unit;