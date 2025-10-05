package urlvalidator

import (
	"fmt"
	"strings"
)

func ValidateURL(targetURL string) error {
	if !strings.HasPrefix(targetURL, "http://") && !strings.HasPrefix(targetURL, "https://") {
		return fmt.Errorf("invalid URL: %q (must start with http:// or https://)", targetURL)
	}

	return nil
}
