/*
Copyright © 2025 redseverity <red.severity723@passfwd.com>
*/
package urlverify

import (
	"fmt"
)

// validates if the timeout is >= 0
func Timeout(timeout int) error {
	if timeout < 0 {
		return fmt.Errorf("timeout must be 0 or greater")
	}
	return nil
}
