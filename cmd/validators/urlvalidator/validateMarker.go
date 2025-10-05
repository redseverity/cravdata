/*
Copyright © 2025 redseverity <red.severity723@passfwd.com>
*/
package urlvalidator

import (
	"fmt"
	"strings"

	"github.com/spf13/cobra"
)

func ValidateMarker(targetURL string, cmd *cobra.Command) error {
	marker, _ := cmd.Flags().GetString("marker")

	if strings.TrimSpace(marker) == "" {
		return fmt.Errorf("flag --marker requires a non-empty argument")
	}

	if !strings.Contains(targetURL, marker) {
		return fmt.Errorf("marker %q not found in target URL", marker)
	}

	return nil
}
