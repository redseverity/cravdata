/*
Copyright © 2025 redseverity <red.severity723@passfwd.com>
*/
package urlvalidator

import (
	"fmt"

	"github.com/spf13/cobra"
)

// RequireMinArgs ensures args has at least n elements.
func RequireMinArgs(cmd *cobra.Command, args []string, n int) error {
	if err := cobra.MinimumNArgs(n)(cmd, args); err != nil {
		return fmt.Errorf("%s", err)
	}
	return nil
}
