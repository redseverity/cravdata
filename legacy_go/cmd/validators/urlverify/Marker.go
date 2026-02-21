/*
Copyright © 2025 redseverity <red.severity723@passfwd.com>
*/
package urlverify

import (
	"fmt"
	"strings"
)

func Marker(targetURL *string, marker string) error {

	if strings.TrimSpace(marker) == "" {
		return fmt.Errorf("flag --marker requires a non-empty argument")
	}

	if !strings.Contains(*targetURL, marker) {
		return fmt.Errorf("marker %q not found in target URL", marker)
	}

	*targetURL = strings.Replace(*targetURL, marker, "", 1)

	return nil
}
