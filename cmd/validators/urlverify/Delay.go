/*
Copyright © 2025 redseverity <red.severity723@passfwd.com>
*/
package urlverify

import (
	"fmt"
)

// validates if the delay is >= 0
func Delay(delay int) error {
	if delay < 0 {
		return fmt.Errorf("delay must be 0 or greater")
	}
	return nil
}
