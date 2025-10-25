/*
Copyright © 2025 redseverity <red.severity723@passfwd.com>
*/
package urlvalidator

import "fmt"

// Max validates that max is greater than or equal to min
func Max(max int, min int) error {
	if max < min {
		return fmt.Errorf("max must be greater than or equal to min (min: %d)", min)
	}
	return nil
}
