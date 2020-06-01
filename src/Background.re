type onHistoryStateUpdatedEvent;
[@bs.val] [@bs.scope ("chrome", "webNavigation", "onHistoryStateUpdated")]
external onHistoryStateUpdatedEventAddListener: (onHistoryStateUpdatedEvent => unit) => unit = "addListener";

onHistoryStateUpdatedEventAddListener(_ev => {
  Chrome_Tabs.query(
    Chrome_Tabs.makeQueryInfo(~active=true, ~currentWindow=true, ()),
    tabs => {
      let tab = Belt.Array.get(tabs, 0);
      if (Belt.Option.isSome(tab)) {
        let tab = Belt.Option.getExn(tab);
        if (Belt.Option.isSome(tab.id)) {
          let tabId = Belt.Option.getExn(tab.id);
          Chrome_Tabs.sendMessage(tabId, `renderCopyFileButton, _ => ());
        };
      };
    },
  )
});