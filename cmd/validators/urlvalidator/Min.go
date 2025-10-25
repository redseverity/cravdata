/*
Copyright © 2025 redseverity <red.severity723@passfwd.com>
*/
package urlvalidator

import (
	"fmt"
)

// Min validates that min is >= 1 and <= max
func Min(min int, max int) error {
	if min < 1 {
		return fmt.Errorf("min must be at least 1")
	}
	return nil
}
