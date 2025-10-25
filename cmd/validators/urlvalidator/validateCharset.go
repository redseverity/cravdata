/*
Copyright © 2025 redseverity <red.severity723@passfwd.com>
*/

package urlvalidator

import (
	"fmt"
	"regexp"
	"strings"
)

// ValidateCharset checks if the provided charset contains only characters
// allowed by RFC 3986 for use in URLs (both reserved and unreserved).
func ValidateCharset(charset *string) error {
	// RFC 3986 valid characters:
	// unreserved  = ALPHA / DIGIT / "-" / "." / "_" / "~"
	// reserved    = gen-delims / sub-delims
	// gen-delims  = ":" / "/" / "?" / "#" / "[" / "]" / "@"
	// sub-delims  = "!" / "$" / "&" / "'" / "(" / ")" / "*" / "+" / "," / ";" / "="
	var validCharset = regexp.MustCompile(`^[a-zA-Z0-9\-._~:/?#\[\]@!$&'()*+,;=]+$`)

	if !validCharset.MatchString(*charset) {
		return fmt.Errorf(`invalid charset provided.
supported characters (RFC 3986):
a-z A-Z 0-9 - _ . ~ : / ? # [ ] @ ! $ & ' ( ) * + , ; =`)
	}

	// Remove duplicates while preserving order
	var seen = make(map[rune]bool)
	var cleaned strings.Builder

	for _, char := range *charset {
		if !seen[char] {
			seen[char] = true
			cleaned.WriteRune(char)
		}
	}

	*charset = cleaned.String()

	return nil
}
