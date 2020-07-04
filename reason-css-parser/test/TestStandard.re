open TestFramework;
open Reason_css_parser;
open Standard;
open Parser;

// TODO: case insensitive
describe("standard values", ({test, _}) => {
  test("<integer>", ({expect, _}) => {
    let parse = parse([%value "<integer>"]);
    expect.result(parse("54")).toBe(Ok(54));
    expect.result(parse("54.5")).toBeError();
  });
  test("<number>", ({expect, _}) => {
    let parse = parse([%value "<number>"]);
    expect.result(parse("55")).toBe(Ok(55.));
    expect.result(parse("55.5")).toBe(Ok(55.5));
    expect.result(parse("ident")).toBeError();
  });
  test("<length>", ({expect, _}) => {
    let parse = parse([%value "<length>"]);
    expect.result(parse("56cm")).toBe(Ok(`Cm(56.)));
    expect.result(parse("57px")).toBe(Ok(`Px(57.)));
    expect.result(parse("59invalid")).toBeError();

    expect.result(parse("0")).toBe(Ok(`Zero));
    expect.result(parse("60")).toBeError();
  });
  test("<percentage>", ({expect, _}) => {
    let parse = parse([%value "<percentage>"]);
    expect.result(parse("61%")).toBe(Ok(61.));
    expect.result(parse("62.3%")).toBe(Ok(62.3));
    expect.result(parse("63.4:")).toBeError();
  });
  test("<length-percentage>", ({expect, _}) => {
    let parse = parse([%value "<length-percentage>"]);
    expect.result(parse("64cm")).toBe(Ok(`Length(`Cm(64.))));
    expect.result(parse("65%")).toBe(Ok(`Percentage(65.)));
    expect.result(parse("66dsa")).toBeError();
  });
  test("keyword", ({expect, _}) => {
    let parse = parse([%value "gintoki"]);
    expect.result(parse("gintoki")).toBe(Ok());
    expect.result(parse("nope")).toBeError();
  });
  test("<css-wide-keywords>", ({expect, _}) => {
    let parse = parse([%value "<css-wide-keywords>"]);
    expect.result(parse("initial")).toBe(Ok(`Initial));
    expect.result(parse("inherit")).toBe(Ok(`Inherit));
    expect.result(parse("unset")).toBe(Ok(`Unset));
    expect.result(parse("nope")).toBeError();
  });
  test("<string>", ({expect, _}) => {
    let parse = parse([%value "<string>"]);
    expect.result(parse("'tuturu'")).toBe(Ok("tuturu"));
    expect.result(parse("'67.8'")).toBe(Ok("67.8"));
    expect.result(parse("ident")).toBeError();
    expect.result(parse("68.9")).toBeError();
  });
  test("<custom-ident>", ({expect, _}) => {
    let parse = parse([%value "<custom-ident>"]);
    expect.result(parse("potato")).toBe(Ok("potato"));
    expect.result(parse("'mayushii'")).toBeError();
    expect.result(parse("68.9")).toBeError();
  });
  test("<dashed-ident>", ({expect, _}) => {
    let parse = parse([%value "<dashed-ident>"]);
    expect.result(parse("--random")).toBe(Ok("--random"));
    expect.result(parse("random'")).toBeError();
  });
  test("<url>", ({expect, _}) => {
    let parse = parse([%value "<url>"]);
    expect.result(parse("url(https://google.com)")).toBe(
      Ok("https://google.com"),
    );
    expect.result(parse("url(\"https://duckduckgo.com\")")).toBe(
      Ok("https://duckduckgo.com"),
    );
  });
});
