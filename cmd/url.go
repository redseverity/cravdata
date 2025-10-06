/*
Copyright © 2025 redseverity <red.severity723@passfwd.com>
*/
package cmd

import (
	"github.com/redseverity/cravdata/cmd/validators/urlvalidator"
	"github.com/spf13/cobra"
)

var (
	targetURL string
	marker    string
)

// urlCmd represents the url command
var urlCmd = &cobra.Command{
	Use:   "url [target-url]",
	Short: "Discover target URLs",
	Long: `The "url" subcommand discovers valid URLs by replacing a marker in a template with words generated
dynamically (no wordlists required) and probing the resulting addresses. Use the default marker
{BRUTE} or override it with the "--marker" / "-m" flag.

Flags (detailed):
  -m, --marker string
      Marker placeholder used in the target template where dynamically generated words
      will be inserted. By default the marker is "{BRUTE}". Use a custom marker if the
      template uses a different token (e.g. --marker=$$$ or --marker=HERE).

Examples:
  cravdata url "{BRUTE}.example.com/users"
  cravdata url "www.$$$.com/users" --marker=$$$`,
	Args: func(cmd *cobra.Command, args []string) error {
		if err := cobra.MinimumNArgs(1)(cmd, args); err != nil {
			return err
		}

		targetURL = args[0]
		if err := urlvalidator.ValidateURL(targetURL); err != nil {
			return err
		}

		if err := urlvalidator.ValidateMarker(targetURL, marker); err != nil {
			return err
		}

		return nil
	},

	RunE: func(cmd *cobra.Command, args []string) error {
		return nil
	},
}

func init() {
	rootCmd.AddCommand(urlCmd)
	urlCmd.Flags().StringVarP(&marker, "marker", "m", "{BRUTE}", "placeholder for inserting generated words")
}
