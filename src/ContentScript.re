let getFileText = () => {
  open Webapi.Dom;
  open Belt.Option;
  let result = ref("");
  let codeViewerElement = Document.querySelector("[itemprop='text'", document);
  if (isSome(codeViewerElement)) {
    let codeViewerElement = getExn(codeViewerElement);
    let lineNumberElements = Element.querySelectorAll(".blob-num", codeViewerElement);
    lineNumberElements
    |> NodeList.forEach((node, _i) => {
         Element.setAttribute("style", "display:none;", Obj.magic(node));
         ();
       });
    result := Element.innerText(codeViewerElement);
    lineNumberElements
    |> NodeList.forEach((node, _i) => {
         Element.setAttribute("style", "display:block;", Obj.magic(node));
         ();
       });
    ();
  };
  result^;
};

let copyTextToClipboard = text => {
  open Webapi.Dom;
  open Belt.Option;
  let textElement = Document.createElement("textarea", document);
  Element.setTextContent(textElement, text);
  let body = Document.unsafeAsHtmlDocument(document) |> HtmlDocument.body;
  if (isSome(body)) {
    let body = getExn(body);
    Element.appendChild(textElement, body);
    HtmlInputElement.select(Obj.magic(textElement));
    DocumentBindings.execCommand1("copy") |> ignore;
    HtmlInputElement.blur(Obj.magic(textElement));
    Element.removeChild(textElement, body) |> ignore;
    ();
  };
};

let renderCopyButton = () => {
  open Webapi.Dom;
  open Belt.Option;
  let copyFileBtnId = "github-copy-file-extension-copy-file-btn";
  let copyFileBtnElement = Document.querySelector("#" ++ copyFileBtnId, document);
  if (isNone(copyFileBtnElement)) {
    //note(itay): Assuming we're good to render the button if there's a Raw button on the page
    //which seems to appear on pages where there are files in view mode.
    let rawUrlElement = Document.querySelector("#raw-url", document);
    if (isSome(rawUrlElement)) {
      let rawUrlElement = getExn(rawUrlElement);
      let btnGroupElement = Element.parentElement(rawUrlElement);
      if (isSome(btnGroupElement)) {
        let btnGroupElement = getExn(btnGroupElement);
        let copyFileButton = Document.createElement("div", document);
        Element.setAttribute("id", copyFileBtnId, copyFileButton);
        Element.setAttribute("class", "btn btn-sm BtnGroup-item", copyFileButton);
        Element.addClickEventListener(_ev => {getFileText() |> copyTextToClipboard}, copyFileButton);
        Element.setTextContent(copyFileButton, "Copy file");
        Element.insertBefore(copyFileButton, rawUrlElement, btnGroupElement) |> ignore;
        ();
      };
    };
  };
};

let setup = () => {
  Chrome_Runtime.OnMessage.addListener((request, _sender, _sendResponse) => {
    switch (request) {
    | `renderCopyFileButton => renderCopyButton()
    }
  });
  renderCopyButton();
};

setup();