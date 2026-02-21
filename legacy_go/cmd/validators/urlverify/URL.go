/*
Copyright © 2025 redseverity <red.severity723@passfwd.com>
*/
package urlverify

import (
	"fmt"
	"strings"
)

func URL(targetURL string) error {
	if !strings.HasPrefix(targetURL, "http://") && !strings.HasPrefix(targetURL, "https://") {
		return fmt.Errorf("invalid URL: %q (must start with http:// or https://)", targetURL)
	}

	return nil
}
