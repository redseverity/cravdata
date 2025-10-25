/*
Copyright © 2025 redseverity <red.severity723@passfwd.com>
*/
package urldocs

const (
	Use = "url [target-url]"

	Short = "Discover target URLs"

	Long = `The "url" subcommand discovers valid URLs by replacing a marker in a template with words generated
dynamically (no wordlists required) and probing the resulting addresses.`

	Charset = `Characters to use when generating words for the brute-force/template substitution.
Provide the exact set of characters you want (duplicates will be removed and order 
preserved). The provided charset **must** contain only characters allowed by RFC 3986 
(unreserved + reserved). If the charset contains invalid characters the program will 
return an error and refuse to run.`

	Marker = `Marker placeholder used in the target template where dynamically generated words 
will be inserted. By default the marker is "{BRUTE}". Use a custom marker if the
template uses a different token.`
)
